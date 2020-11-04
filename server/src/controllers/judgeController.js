const { spawn } = require('child_process');
const fs = require('fs');
const models = require('../models');

exports.judge = function(req, res) {
    const USERID = req.body.userid;
    const PROBNO = 1;
    const CODE = decodeEntities(req.body.code);
    const LANG = req.body.lang;
    const LANGKIND = LANG.substring(1, LANG.length);

    models.history.create({
        probNo: PROBNO,
        userId: USERID,
        lang: LANG,
        time: TIME
    })
    .then(res => {
        console.log('insert complete');

        const MARKNO = res['markNo'];
        let EXTENSION;

        // console.log(LANG[0]);
        switch(LANG[0]) {
            case '0': EXTENSION = 'cpp'; break;
            case '1': EXTENSION = 'py'; break;
            case '2': EXTENSION = 'py'; break;
        }

        fs.mkdirSync(`/home/Codieater/src/volumes/mark_no/${MARKNO}`);
        fs.writeFileSync(`/home/Codieater/src/volumes/mark_no/${MARKNO}/Main.` + EXTENSION, CODE, function (e) {
            if(e) {
                console.log('file write fail');
                console.log(e);
            }
        });

        const JUDGERES = system(USERID, PROBNO, LANGKIND);

        res.render('../views/judge/index.ejs', {
            USERID: USERID,
            PROBNO: PROBNO,
            CODE: CODE,
            LANG: LANGKIND,
            JUDGERES: JUDGERES
        });
    })
    .catch(e => {
        console.log('insert fail');
        console.log(e);

        res.status(500).json({ error: 'something go wrong' });
    });

    // res.render('../views/judge/index.ejs', {
    //     USERID: USERID,
    //     PROBNO: PROBNO,
    //     CODE: CODE,
    //     LANG: LANGKIND,
    // });
}

// USERID => CODE DIR
// PROBNO => IN/OUT DIR
const system = function (USERID, PROBNO, LANGKIND) {
    let json;

    const docker = spawn('docker', [
        'run',
        '--rm',
        '-v', '/Users/redundant4u/Documents/project/Codieater/server/src/volumes:/home/judge/volumes',
        'judge:1.0', 'sh', '-c', `./main -l ${LANGKIND} -c ${USERID} -d ${PROBNO}`
    ]);

    docker.stdout.on('data', (data) => {
        const file = fs.readFileSync(`./volumes/mark_no/${USERID}/result.json`);
        json = JSON.parse(file);

        let query = { 'result': 0, 'score': 0 };
    
        // compile complete
        if( json.compile == 1 ) {
            const length = Object.keys(json.result).length
            let score = 0;
    
            // 채점 결과의 msg들을 순서대로 보여주고 점수 계산
            // for( let i = 0; i < length; i++ ) score += json.result[i].check;
            json['result'].forEach(elem => score += parseInt(elem['check']));
            score = Math.floor( score / length * 100 );
    
            query['result'] = 1;
            query = { 'result': 1, 'score': score };
        }

        models.history.update(query, { where: {userId: USERID} })
        .then(res => {
            console.log('history result is updated');
            console.log(res);
        })
        .catch(e => {
            console.log('history result update fail');
            console.log(e);
        })

        // console.log( json.compile_msg );
        // console.log(`stdout: ${data}`);
    });
    
    docker.stderr.on('data', (data) => { console.error(`stderr: ${data}`); });
    
    docker.on('close', (code) => {
        console.log(`child process exited with code ${code}`);
        return json;
    });
}

// for test
const decodeEntities = function (encodedString) {
    var translate_re = /&(nbsp|amp|quot|lt|gt);/g;
    var translate = {
        "nbsp":" ",
        "amp" : "&",
        "quot": "\"",
        "lt"  : "<",
        "gt"  : ">"
    };
    return encodedString.replace(translate_re, function(match, entity) {
        return translate[entity];
    }).replace(/&#(\d+);/gi, function(match, numStr) {
        var num = parseInt(numStr, 10);
        return String.fromCharCode(num);
    });
}