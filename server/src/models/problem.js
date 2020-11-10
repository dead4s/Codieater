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
    memoryLim: DataTypes.SMALLINT,
    // create_at: DataTypes.DATE
  }, { tableName: 'problem' });

  problem.associate = function(models) {
    problem.belongsTo(models.user, {
      as: 'user',
      foreignKey: 'userId',
      onDelete: 'CASCADE',
    });

    problem.belongsToMany(models.tag, {
      through: 'problem_tag',
      as: 'tags',
      foreignKey: 'probNo',
      onDelete: 'CASCADE',
    });
  };

  return problem;
};