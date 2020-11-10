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
        console.log(e);
    });

    // res.render('../views/problem/register.ejs');
}

exports.registerPost = function (req, res) {
    console.log(req.body['description']);

    // db.problem.create({
    //     decription: req.body['']
    // })

    res.send('ho');
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