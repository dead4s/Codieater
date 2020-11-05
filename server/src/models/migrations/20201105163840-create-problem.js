module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('problem', {
      probNo: {
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      userId: {
        type: Sequelize.INTEGER,
        references: {
              model: 'user',
              key: 'idx',
        },
        allowNull: false,
      },
      description: {
        type: Sequelize.TEXT,
      },
      timeLim: {
        type: Sequelize.REAL,
      },
      memoryLim: {
        type: Sequelize.SMALLINT,
      },
      // create_at: {
      //   type: Sequelize.DATE,
      //   allowNull: false,
      // },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('problem'),
};