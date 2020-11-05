'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('history', [{
      probNo: 1,
      userId: 2,
      // code: '#include <stdio.h> int main(void) { printf("1\n"); } )',
      lang: 'CPP',
      time: 0.5,
      memory: 10,
      size: 200,
      result: 0,
      // create_at: new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''),
    }], {});
  },

  down: (queryInterface, Sequelize) => {
      return queryInterface.bulkDelete('history', null, {});
  }
};