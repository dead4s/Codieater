const router = require('express').Router();
const multer = require('multer');
const upload = multer();

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
router.post('/problem/register', 
    upload.fields([
        { name: 'inputfile', maxCount: 50 },
        { name: 'outputfile', maxCount: 50 }
    ]),
    problemController.registerPost);

router.get('/judge', judgeController.judgeGet);
router.post('/judge', judgeController.judgePost);

router.get('/info', userController.infoGet);
router.post('/info', userController.infoPost);

module.exports = router;