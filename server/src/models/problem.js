'use strict';
module.exports = (sequelize, DataTypes) => {
  const problem = sequelize.define('problem', {
    probNo: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true,
      allowNull: false,
    },
    description: DataTypes.TEXT,
    timeLim: DataTypes.REAL,
    memeoryLim: DataTypes.SMALLINT,
    // create_at: DataTypes.DATE
  }, { tableName: 'problem' });
  problem.associate = function(models) {
    // associations can be defined here
    problem.belongsTo(models.user, {
      foreignKey: 'userId',
      as: 'idx',
      onDelete: 'CASCADE',
    });
  };
  return problem;
};