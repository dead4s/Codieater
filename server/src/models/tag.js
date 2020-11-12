'use strict';
module.exports = (sequelize, DataTypes) => {
  const tag = sequelize.define('tag', {
    tagId: {
      type: DataTypes.INTEGER,
      allowNull: false,
      autoIncrement: true,
      primaryKey: true,
    },
    tagName: DataTypes.STRING(30),
  }, { tableName: 'tag' });

  tag.associate = function(models) {
    tag.belongsToMany(models.problem, {
      through: 'problem_tag',
      // as: 'problem',
      foreignKey: 'tagId',
      // onDelete: 'CASCADE',
    });
  };

  return tag;
};