module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('user', {
      idx: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER,
      },
      id: {
        type: Sequelize.STRING(30),
        unique: true,
        allowNull: false,
      },
      pwd: {
        type: Sequelize.STRING(130),
        allowNull: false,
      },
      kind: {
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      name: {
        type: Sequelize.STRING(20),
        allowNull: false,
      },
      email: {
        type: Sequelize.STRING(50),
      },
      phone: {
        type: Sequelize.STRING(30),
      },
      date: {
        type: Sequelize.DATE,
        allowNull: false,
      },
      error_count: {
        type: Sequelize.INTEGER,
        allowNull: false,
      },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('user'),
};
