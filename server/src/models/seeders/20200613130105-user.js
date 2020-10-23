const faker = require('faker');
const bcrypt = require('bcryptjs');

const kind = [0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,4]
const user = [...Array(20)].map((user, index) => ({
  id: faker.finance.bic(),
  pwd: bcrypt.hashSync('1q2w3e4r!', bcrypt.genSaltSync(10), null),
  kind: kind[index],
  name: faker.name.lastName() + faker.name.firstName(),
  email: faker.internet.email(),
  phone: faker.phone.phoneNumber(),
  error_count: 0,
  date: faker.date.recent(),
}));

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('user', user, {});
  },

  down: (queryInterface, Sequelize) => {
    return queryInterface.bulkDelete('user', null, {});
  },
};
