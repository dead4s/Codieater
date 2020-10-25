const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const db = require('../models');

passport.use(
  new LocalStrategy(
    {
      usernameField: 'id',
      passwordField: 'pwd',
      passReqToCallback: true,
    },

    (req, id, pwd, done) => {
      db.user.findOne({
        where: {
          id,
        },
      }).then((dbUser) => {
        if (!dbUser) {
          return done(null, false, {
            code: 47,
            data: { msg: 'Incorrect id.', err: 'Incorrect id.' },
          });
        }
        if (!dbUser.validPassword(pwd)) {
          dbUser.increaseError();
          return done(null, false, {
            code: 48,
            data: { msg: 'Incorrect password.', err: 'Incorrect password.' },
          });
        }
        if (!dbUser.checkError()) {
          return done(null, false, {
            code: 49,
            data: { msg: 'Maximum number of login attempts exceeded. Please contact your administrator.', err: 'Maximum number of login attempts exceeded. Please contact your administrator.' },
          });
        }
        dbUser.resetError();
        return done(null, dbUser);
      });
    }
  )
);

passport.serializeUser((user, cb) => {
  cb(null, user);
});

passport.deserializeUser((obj, cb) => {
  cb(null, obj);
});

module.exports = passport;
