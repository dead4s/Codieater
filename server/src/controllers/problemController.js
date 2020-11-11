const db = require('../models');

exports.index = function (req, res) {
    res.render('../views/problem/index.ejs');
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

exports.registerPost = function (req, res) {
    const TITLE = req.body['title'];
    const DESCRIPTION = req.body['description'];
    const MEM = req.body['memory'];
    const TIME = req.body['time'];
    const INPUT = req.body['input'];
    const OUTPUT = req.body['output'];
    const SAMPLEINPUT = req.body['sampleinput'];
    const SAMPLEOUTPUT = req.body['sampleoutput'];
    const TAGS = req.body['tag'];

    let tagsId = [];

    // if tag is new, create
    TAGS.forEach(elem => {
        db.tag.findAll({
            raw: true,
            attributes: [ 'tagId', 'tagName' ],
            where: { tagName: elem }
        })
        .then(q => {
            // if tag is new
            if(!q[0]) {
                console.log(q[0]);
                db.tag.create({
                    tagName: elem
                })
                .then(q => {
                    console.log('tag insertion success');
                })
                .catch(e => {
                    console.log('tag insertion failed');
                })
            }

            tagsId.push(q[0]['tagId']);
        })
        .catch(e => {
            // console.log(e);
        })
    });

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
        // console.log(e);

    });

    res.redirect('/');
}

exports.test = function (req, res) {
    try{
    db.problem.findAll({
        raw: true,
        include: [{
            model: db.tag,
            as: 'tags',
            attributes: [ 'tagId', 'tagName' ],
            where:  { tagId: 2 }
        }]
    })
    .then(q => {
        console.log(q);
        console.log(q[0]["tags.tagName"]);
        // console.log(q);
    })
    .catch(e => {
        console.log(e);
        console.log('error');
    });
    }
    catch(e) { console.log(e); }

    res.send('hi');
}