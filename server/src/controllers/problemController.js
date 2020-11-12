require('dotenv').config();

const db = require('../models');
const fs = require('fs');
const PWD = process.env.WORKDIR;

exports.index = async function (req, res) {
    const listCount = 15; 
    
    //get total problem number
    const totalProblem = await db.problem.findAndCountAll();
    const totalCount = totalProblem["count"]; 
    let pageCount = Math.ceil(totalCount / listCount); 
    
    //current page and page range
    let reqPage = req.query.page; 
    let currentPage = parseInt(reqPage); 
    if(!currentPage)
        currentPage = 1;  
    if( currentPage > pageCount)
        currentPage = pageCount; 
    if (currentPage <= 0)
        currentPage = 1;     

    let pageNavStart = currentPage - 2;  
    if(pageNavStart <= 0)
        pageNavStart = 1;
    let pageNavEnd = currentPage + 2; 
    if(pageNavEnd > pageCount)
        pageNavEnd = pageCount; 
    

    await db.problem.findAll({
        raw: true,
        offset: (currentPage - 1) * listCount, 
        limit: listCount, 
        attributes: ['probNo', 'title'],
        /* TODO - Help !!! 
        include : [
            {
                model: problem_tag, 
                as : 'tags',    
                attributes: ['tagId', 'tagName'], 
                through : {
                    attributes: [], 
                }
            },
        ]
        */
    })
    .then (q => {
        console.log(q); 
        console.log('success'); 
        res.render('../views/problem/index.ejs', {PLIST : q, PGSTART : pageNavStart, PGEND : pageNavEnd, PGCURRENT : currentPage});
    })
    .catch(e => {
        console.log(q); 
        console.log('error while loading problemlist'); 
    });
}

exports.problemGet = async function(req, res){    
    await db.problem.findOne({
        raw: true,
        where : {probNo: req.params.no}
        //attributes: ['probNo', 'title', 'userId', 'description', 'memoryLim', 'timeLim', 'sampleInput', 'sampleOutput'],
        /* TODO - Help !!! 
            출제자 id, 
            태그 정보 
        */
    })
    .then (q => {
        console.log(q); 
        console.log('success'); 
        if(!q){
            console.log("wrong problem number back to problem list"); 
            res.redirect('/problem')
        }
        res.render('../views/problem/info.ejs', {PINFO : q}); 
    })
    .catch(e => {
        console.log(q); 
        console.log('error while loading problemlist'); 
    });
}


exports.registerGet = function (req, res) {
    db.tag.findAll({
        attributes: ['tagName'],
        raw: true
    })
    .then(q => {
        console.log(q);
        res.render( '../views/problem/register.ejs', {TAGS: q} );
    })
    .catch(e => {
        console.log('fail to load tags');
        // console.log(e);

        res.redirect('/');
    });
}

exports.registerPost = async function (req, res) {
    const TITLE         =   req.body['title'];
    const DESCRIPTION   =   req.body['description'];
    const MEM           =   req.body['memory'];
    const TIME          =   req.body['time'];
    const INPUT         =   req.body['input'];
    const OUTPUT        =   req.body['output'];
    const INPUTFILE     =   req.files['inputfile'];
    const OUTPUTFILE    =   req.files['outputfile'];
    const SAMPLEINPUT   =   req.body['sampleinput'];
    const SAMPLEOUTPUT  =   req.body['sampleoutput'];
    let TAGS;

    // tag가 하나 일 때는 array가 아닌 string으로 인식해서 변환
    if( typeof(req.body['tag']) == 'string' )
        TAGS = req.body['tag'].split();
    else 
        TAGS = req.body['tag'];

    let tagsId = [];

    // if tag is new, create
    for( let i = 0; i < TAGS.length; i++ ) {
        await db.tag.findAll({
            raw: true,
            attributes: [ 'tagId', 'tagName' ],
            where: { tagName: TAGS[i] }
        })
        .then(q => {
            // if tag is new
            if(!q[0]) {
                db.tag.create({
                    tagName: TAGS[i]
                })
                .then(q => {
                    tagsId.push(q['tagId']);
                    console.log('tag insertion success');
                })
                .catch(e => {
                    console.log('tag insertion failed');
                })
            }

            else tagsId.push(q[0]['tagId']);
        })
        .catch(e => {
            // console.log(e);
        })
    }

    // create problem
    db.problem.create({
        userId: 1,
        title: TITLE,
        description: DESCRIPTION,
        memoryLim: MEM,
        timeLim: TIME,
        input: INPUT,
        output: OUTPUT,
        sampleInput: SAMPLEINPUT,
        sampleOutput: SAMPLEOUTPUT,
    })
    .then(q => {
        // insert input, output data
        const PATH = `${PWD}/volume/prob_no/` + q['probNo'];
        const INPATH = `${PWD}/volume/prob_no/` + q['probNo'] + '/in';
        const OUTPATH = `${PWD}/volume/prob_no/` + q['probNo'] + '/out';

        fs.mkdirSync(PATH);
        fs.mkdirSync(INPATH);
        fs.mkdirSync(OUTPATH);

        for( let i = 1; i < INPUTFILE.length + 1; i++ ) {
            fs.writeFileSync( INPATH + '/' + i + '.in', INPUTFILE[i-1].buffer, function(e) {
                if(e) {
                    console.log('input file insertion failed');
                    console.log(e);
                }
            });

            fs.writeFileSync( OUTPATH + '/' + i + '.out', OUTPUTFILE[i-1].buffer, function(e) {
                if(e) {
                    console.log('output file insertion failed');
                    console.log(e);
                }
            });
        }

        // tag connect
        tagsId.forEach(elem => {
            db.problem_tag.create({
                probNo: q['probNo'],
                tagId: elem
            })
            .then(q => {
                console.log('tag connect');
                // console.log(q);
            })
            .catch(e => {
                console.log('tag connect failed');
                // console.log(e);
            })
        })

        console.log('problem insertion success');
        // console.log(q);
    })
    .catch(e => {
        console.log('problem insertion failed');
        console.log(e);

    });

    res.redirect('/');
}