const express = require('express');
const { check, validationResult } = require('express-validator');
const userController = require('../../controllers/userController');
const passport = require('../../utils/passport');
const auth = require('../auth');
const router = express.Router();

const idValidator = [check('id').exists().withMessage('id is not null')];

const pwdValidator = [check('pwd').exists().withMessage('id is not null')];

const emailValidator = [
  check('email').exists().withMessage('id is not null'),
  check('email').isEmail().withMessage('email format is not correct'),
];

const signupValidator = [
  check('name').exists().withMessage('name is not null'),
  check('phone').exists().withMessage('phone is not null'),
]
  .concat(idValidator)
  .concat(pwdValidator)
  .concat(emailValidator);

router.post('/login', idValidator.concat(pwdValidator), function (
  req,
  res,
  next
) {
  try {
    const errors = validationResult(req).array();

    if (errors.length > 0) {
      req.session.errors = errors;
      req.session.success = false;
      res
        .status(400)
        .json({ code: 43, data: { msg: 'Validation errors', err: errors } });
    } else {
      passport.authenticate('local', function (err, user, info) {
        if (err) return next(err);
        if (!user) return res.status(400).json({ ...info });
        req.login(user, function (err) {
          if (err) {
            return next(err);
          }
          return res
            .status(200)
            .json({ code: 0, data: { msg: 'Success', items: user } });
        });
      })(req, res, next);
    }
  } catch (err) {
    return next(err, req, res, next);
  }
});
router.post('/signup', signupValidator, userController.signup);
router.post(
  '/findpw',
  idValidator.concat(emailValidator),
  userController.passwordFind
);
router.get('/logout', auth, userController.logout);
router.get('/check', auth, userController.check);

module.exports = router;
