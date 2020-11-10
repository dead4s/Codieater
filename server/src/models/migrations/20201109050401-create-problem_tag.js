'use strict';

module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('problem_tag', {
      probNo: {
        type: Sequelize.INTEGER,
        allowNull: false,
        references: {
          model: 'problem',
          key: 'probNo'
        }
      },
      tagId: {
        type: Sequelize.INTEGER,
        allowNull: false,
        references: {
          model: 'tag',
          key: 'tagId'
        }
      }
    }),

  down: (queryInterface, Sequelize) => queryInterface.dropTable('problem_tag'),
};
