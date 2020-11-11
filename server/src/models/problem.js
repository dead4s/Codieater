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
    sampleOutput: DataTypes.TEXT
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