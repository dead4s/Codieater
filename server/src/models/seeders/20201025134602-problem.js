'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('problem', [{
      user_id: 1,
      description: "sample description",
      time_lim: 1,
      memory_lim: 2,
      create_at: new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''),
    }], {});
  },

  down: (queryInterface, Sequelize) => {
    return queryInterface.bulkDelete('problem', null, {});
  }
};