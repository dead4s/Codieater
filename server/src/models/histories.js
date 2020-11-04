const moment = require('moment');

'use strict';
module.exports = (sequelize, DataTypes) => {
  const histories = sequelize.define('histories', {
    mark_no: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true,
      allowNull: false,
    },
    // code: DataTypes.TEXT,
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
  }, {});
  // history.associate = function(models) {
  //   // associations can be defined here
  //   history.belongsTo(models.user, {
  //     foreignKey: 'idx',
  //     as: 'user_id',
  //     onDelete: 'CASCADE',
  //   });

  //   history.belongsTo(models.problem, {
  //     foreignKey: 'prob_no',
  //     as: 'prob_nos',
  //     onDelete: 'CASCADE'
  //   });
  // };
  return histories;
};