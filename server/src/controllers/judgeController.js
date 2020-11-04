// require('dotenv').config({ path: "../.env" });

const { env } = require('process');
// const { Client } = require('pg');
const fs = require('fs');
const db = require('../models');
const histories = require('../models/histories')
const View = '../views/judge';

// const client = new Client({
//     host: env.HOST,
//     database: env.DATABASE,
//     user: env.USERNAME,
//     password: env.PASSWORD,
//     port: 5432,
// });

exports.judge = function(req, res) {
    const USERID = req.body.userid;
    const PROBNO = 1;
    const CODE = decodeEntities(req.body.code);
    const LANG = req.body.lang;
    const TIME = 1;

    
    try {
        // const histories = db.histories;
        // histories.sequelize.query('SELECT * FROM histories');
    }
    catch(e) { console.log(e); }

    // client
    //     .connect()
    //     .then(() => console.log('connected'))
    //     .catch(err => console.error('connection error', err.stack))

    // client
    //     .query(
    //         // query, values
    //         'INSERT INTO history (prob_no, user_id, lang, time, create_at) VALUES ($1, $2, $3, $4, $5)',
    //         [PROBNO, USERID, LANG, TIME, new Date()]
    //     )
    //     .then(res => {
    //         client.query('SELECT mark_no FROM history WHERE user_id = $1 ORDER BY mark_no DESC LIMIT 1', [USERID]).then(res => {
    //             // console.log(res['rows'][0].mark_no);
    //             MARKNO = res['rows'][0].mark_no;
    //             try {
    //                 fs.mkdirSync(`/home/Codieater/src/volumes/mark_no/${MARKNO}`);
    //                 fs.writeFileSync(`/home/Codieater/src/volumes/mark_no/${MARKNO}/Main.cpp`, CODE, function (err) {
    //                     if(err) console.log(err);
    //                 });
    //             }
    //             catch(e) { console.log(e); }
    //         })

    //         // console.log(res);
    //     })
    //     .catch(e => console.log(e.stack))

    res.render( View + '/index.ejs', {
        USERID: USERID,
        PROBNO: PROBNO,
        CODE: CODE,
        LANG: LANG,
        TIME: TIME
    });
}

function decodeEntities(encodedString) {
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