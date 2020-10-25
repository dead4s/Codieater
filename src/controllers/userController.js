const { validationResult } = require('express-validator');
const db = require('../models');

exports.signup = (req, res, next) => {
  try {
    const errors = validationResult(req).array();

    if (errors.length > 0) {
      req.session.errors = errors;
      req.session.success = false;
      res
        .status(400)
        .json({ code: 43, data: { msg: 'Validation errors', err: errors } });
    } else {
      db.user
        .create({
          ...req.body,
          kind: 1,
          date: new Date().toString(),
          error_count: 0,
        })
        .then(() => {
          res.status(201).json({ code: 0, data: { msg: 'Signup Successful' } });
        })
        .catch((err) => {
          res.status(500).json({
            code: 500,
            data: { msg: 'Internal Server Error', err: err },
          });
        });
    }
  } catch (err) {
    return next(err, req, res, next);
  }
};

exports.logout = (req, res) => {
  req.logout();
  res.status(200).json({ code: 0, data: { msg: 'Logout Successful' } });
};

exports.check = (req, res) => {
  res.status(200).json({ code: 0, data: { msg: 'Authenticated' } });
};

exports.passwordFind = (req, res, next) => {
  try {
    const errors = validationResult(req).array();

    if (errors.length > 0) {
      req.session.errors = errors;
      req.session.success = false;
      res
        .status(400)
        .json({ code: 43, data: { msg: 'Validation errors', err: errors } });
    } else {
      db.user
        .findOne({
          where: {
            id: req.body.id,
            email: req.body.email,
          },
        })
        .then((dbUser) => {
          if (!dbUser) {
            res.status(200).json({
              code: 21,
              data: {
                msg: 'Information Not Exist',
                err: 'Information Not Exist',
              },
            });
          } else {
            dbUser.resetPwAndError();
            res
              .status(200)
              .json({ code: 0, data: { msg: 'Password Reset Successful' } });
          }
        })
        .catch((err) => {
          res.status(500).json({
            code: 500,
            data: { msg: 'Internal Server Error', err: err },
          });
        });
    }
  } catch (err) {
    return next(err, req, res, next);
  }
};
