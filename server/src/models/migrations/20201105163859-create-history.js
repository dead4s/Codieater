module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('history', {
      markNo: {
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      probNo: {
        type: Sequelize.INTEGER,
        // references: {
        //       model: 'problem',
        //       key: 'probNo',
        // },
        allowNull: false,
      },
      userId: {
        type: Sequelize.INTEGER,
        // references: {
        //   model: 'user',
        //   key: 'idx',
        // }
      },
      lang: {
        type: Sequelize.STRING(10),
      },
      time: {
        type: Sequelize.REAL,
      },
      memory: {
        type: Sequelize.SMALLINT,
      },
      size: {
        type: Sequelize.INTEGER
      },
      result: {
        type: Sequelize.SMALLINT
      },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('history'),
};