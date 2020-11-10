const router = require('express').Router();

const user = require('./api/user');
router.use('/user', user);

const mainController = require('../controllers/mainController');
const userController = require('../controllers/userController');
const problemController = require('../controllers/problemController');
const judgeController = require('../controllers/judgeController');

router.get('/', mainController.index);

router.get('/signup', userController.index);
router.post('/signup', userController.signup);
router.post('/check', userController.check);
router.get('/logout', userController.logout);

router.get('/problem', problemController.index);
router.get('/problem/register', problemController.registerGet);
router.post('/problem/register', problemController.registerPost);

router.get('/judge', judgeController.judgeGet);
router.post('/judge', judgeController.judgePost);

router.get('/test', problemController.test);

module.exports = router;