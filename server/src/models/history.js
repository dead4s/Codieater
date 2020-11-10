const moment = require('moment');

'use strict';
module.exports = (sequelize, DataTypes) => {
  const history = sequelize.define('history', {
    markNo: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true,
      allowNull: false,
    },
    lang: DataTypes.STRING(10),
    time: DataTypes.REAL,
    memory: DataTypes.SMALLINT,
    // create_at: {
    //   type: DataTypes.DATE,
    //   allowNull: false,
    //   get: function () {
    //     const time = this.getDataValue('date');
    //     if (moment(time, moment.ISO_8601, true).isValid()) {
    //       return {
    //         day: moment(time).format('YYYY-MM-DD'),
    //         time: moment(time).format('HH:mm:ss'),
    //       };
    //     }
    //     return time;
    //   },
    // },
  }, { tableName: 'history', });

  history.associate = function(models) {
    history.belongsTo(models.user, {
      foreignKey: 'userId',
      as: 'idx',
      onDelete: 'CASCADE',
    });

    history.belongsTo(models.problem, {
      foreignKey: 'probNo',
      as: 'ProbNo',
      onDelete: 'CASCADE'
    });
  };

  return history;
};