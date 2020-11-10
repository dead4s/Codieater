const faker = require('faker');
const bcrypt = require('bcryptjs');

// const kind = [0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,4]
// const user = [...Array(20)].map((user, index) => ({
//   id: faker.finance.bic(),
//   pwd: bcrypt.hashSync('1q2w3e4r!', bcrypt.genSaltSync(10), null),
//   kind: kind[index],
//   name: faker.name.lastName() + faker.name.firstName(),
//   email: faker.internet.email(),
//   phone: faker.phone.phoneNumber(),
//   error_count: 0,
//   date: faker.date.recent(),
// }));

// module.exports = {
//   up: (queryInterface, Sequelize) => {
//     return queryInterface.bulkInsert('user', user, {});
//   },

//   down: (queryInterface, Sequelize) => {
//     return queryInterface.bulkDelete('user', null, {});
//   },
// };

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('user', [
      {
        id: 'test',
        pwd: bcrypt.hashSync('test', bcrypt.genSaltSync(10), null),
        name: '전설',
        kind: 0,
        email: 'test@test.com',
        error_count: 0,
        date: faker.date.recent()
      },
      {
        id: 'test2',
        pwd: bcrypt.hashSync('test2', bcrypt.genSaltSync(10), null),
        name: '씅',
        kind: 0,
        email: 'test2@test.com',
        error_count: 0,
        date: faker.date.recent()
      }
    ]);
  },

  down: (queryInterface, Sequelize) => {
    return queryInterface.bulkDelete('user', null, {});
  },
}