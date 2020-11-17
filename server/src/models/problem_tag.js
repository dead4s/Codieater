'use strict';

module.exports = (sequelize, DataTypes) => {
  const problem_tag = sequelize.define('problem_tag', {
    probNo: {
      type: DataTypes.INTEGER,
      allowNull: false,
    },
    tagId: {
      type: DataTypes.INTEGER,
      allowNull: false,
    }
  }, { tableName: 'problem_tag' });
 
  problem_tag.associate = function(models) {
    
  };

  return problem_tag;
};