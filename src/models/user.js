const bcrypt = require('bcryptjs');
const moment = require('moment');

module.exports = (sequelize, DataTypes) => {
  const User = sequelize.define(
    'user',
    {
      idx: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: DataTypes.INTEGER,
      },
      id: {
        type: DataTypes.STRING(30),
        unique: true,
        allowNull: false,
      },
      pwd: {
        type: DataTypes.STRING(130),
        allowNull: false,
      },
      kind: {
        type: DataTypes.INTEGER,
        allowNull: false,
      },
      name: {
        type: DataTypes.STRING(20),
        allowNull: false,
      },
      email: DataTypes.STRING(50),
      phone: DataTypes.STRING(30),
      date: {
        type: DataTypes.DATE,
        allowNull: false,
        get: function () {
          const time = this.getDataValue('date');
          if (moment(time, moment.ISO_8601, true).isValid()) {
            return {
              day: moment(time).format('YYYY-MM-DD'),
              time: moment(time).format('HH:mm:ss'),
            };
          }
          return time;
        },
      },
      error_count: {
        type: DataTypes.INTEGER,
        allowNull: false,
      },
    },
    {
      timestamps: false,
      freezeTableName: true,
      tableName: 'user',
    }
  );

  User.prototype.validPassword = function (pwd) {
    return bcrypt.compareSync(pwd, this.pwd);
  };

  User.prototype.increaseError = function () {
    this.error_count += 1;
    this.save();
  };

  User.prototype.checkError = function () {
    if (this.error_count >= 5) return false;
    return true;
  };

  User.prototype.resetPwAndError = function () {
    this.pwd = this.id;
    this.error_count = 0;
    this.save();
  };

  User.prototype.resetError = function () {
    this.error_count = 0;
    this.save();
  };

  User.prototype.toJSON = function () {
    const values = { ...this.get() };
    delete values.pwd;
    return values;
  };

  User.prototype.modifyPw = function (pwd) {
    this.pwd = pwd;
    this.save();
  };

  User.addHook('beforeCreate', (user) => {
    user.pwd = bcrypt.hashSync(user.pwd, bcrypt.genSaltSync(10), null);
  });

  User.addHook('beforeUpdate', (user) => {
    if (user.pwd.indexOf('$2a$10') === -1) {
      user.pwd = bcrypt.hashSync(user.pwd, bcrypt.genSaltSync(10), null);
    }
  });

  return User;
};
