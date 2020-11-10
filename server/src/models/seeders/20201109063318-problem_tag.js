'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('problem_tag', [
      {
        probNo: 1,
        tagId: 2
      },
      {
        probNo: 2,
        tagId: 3
      }
    ], {});
  },

  down: (queryInterface, Sequelize) => {
      return queryInterface.bulkDelete('problem_tag', null, {});
  }
};