const router = require('express').Router();

const user = require('./api/user');
router.use('/user', user);

const mainController = require('../controllers/mainController');
const judgeController = require('../controllers/judgeController');

router.get('/', mainController.index);
router.post('/judge', judgeController.judge);

module.exports = router;
