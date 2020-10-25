const router = require('express').Router();

const user = require('./api/user');

router.use('/user', user);

module.exports = router;
