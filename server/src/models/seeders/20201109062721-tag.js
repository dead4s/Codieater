'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('tag', [
      {
        tagId: 1,
        tagName: '스택'
      },
      {
        tagId: 2,
        tagName: '큐'
      },
      {
        tagId: 3,
        tagName: '알고리즘'
      }
    ], {});
  },

  down: (queryInterface, Sequelize) => {
      return queryInterface.bulkDelete('tag', null, {});
  }
};