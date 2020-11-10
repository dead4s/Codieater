'use strict';

module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('tag', {
      tagId: {
        type: Sequelize.INTEGER,
        autoIncrement: true,
        primaryKey: true,
        allowNull: false,
      },
      tagName: {
        type: Sequelize.STRING(30),
        allowNull: false,
      }
    }),

  down: (queryInterface, Sequelize) => queryInterface.dropTable('tag'),
};
