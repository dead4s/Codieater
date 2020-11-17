'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('history', [
      {
        probNo: 1,
        userId: 1,
        lang: 'CPP14',
        time: 0.5,
        memory: 512,
        size: 200,
        result: 0,
        createAt: new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''),
      }
    ], {});
  },

  down: (queryInterface, Sequelize) => {
      return queryInterface.bulkDelete('history', null, {});
  }
};