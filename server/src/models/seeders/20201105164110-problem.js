'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('problem', [{
      userId: 1,
      description: "sample description",
      timeLim: 1,
      memoryLim: 2,
      // create_at: new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''),
    }], {});
  },

  down: (queryInterface, Sequelize) => {
    return queryInterface.bulkDelete('problem', null, {});
  }
};