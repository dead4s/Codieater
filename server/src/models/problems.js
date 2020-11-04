'use strict';
module.exports = (sequelize, DataTypes) => {
  const problems = sequelize.define('problems', {
    prob_no: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true,
      allowNull: false,
    },
    description: DataTypes.TEXT,
    time_lim: DataTypes.REAL,
    memeory_lim: DataTypes.SMALLINT,
    // create_at: DataTypes.DATE
  }, {});
  problems.associate = function(models) {
    // associations can be defined here
    // problems.belongsTo(models.user, {
    //   foreignKey: 'idx',
    //   as: 'user_id',
    //   onDelete: 'CASCADE',
    // });

    // problems.hasOne(models.history)
  };
  return problems;
};