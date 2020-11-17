const moment = require('moment');

'use strict';
module.exports = (sequelize, DataTypes) => {
  const problem = sequelize.define('problem', {
    probNo: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true,
      allowNull: false,
    },
    title: DataTypes.STRING(30),
    description: DataTypes.TEXT,
    memoryLim: DataTypes.SMALLINT,
    timeLim: DataTypes.REAL,
    input: DataTypes.TEXT,
    output: DataTypes.TEXT,
    sampleInput: DataTypes.TEXT,
    sampleOutput: DataTypes.TEXT,
    createAt: {
      type: DataTypes.DATE,
      // allowNull: false,
      get: function () {
        const time = this.getDataValue('createAt');
        if (moment(time, moment.ISO_8601, true).isValid()) {
          return {
            day: moment(time).format('YYYY-MM-DD'),
            time: moment(time).format('HH:mm:ss'),
          };
        }
        return time;
      },
    },
  }, { tableName: 'problem' });

  problem.associate = function(models) {
    problem.belongsTo(models.user, {
      as: 'user',
      foreignKey: 'userId',
      onDelete: 'CASCADE',
    });

    problem.belongsToMany(models.tag, {
      through: 'problem_tag',
      as: 'tag',
      foreignKey: 'probNo',
      // onDelete: 'CASCADE',
    });

    // problem.hasMany(models.tag, {
    //   foreignKey: 'tagId',
      // as: 'tag'
      // sourceKey: 'tag'
    // })
  };

  return problem;
};