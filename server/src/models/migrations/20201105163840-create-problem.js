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
      title: {
        type: Sequelize.STRING(30)
      },
      description: {
        type: Sequelize.TEXT,
      },
      memoryLim: {
        type: Sequelize.SMALLINT,
      },
      timeLim: {
        type: Sequelize.REAL,
      },
      input: {
        type: Sequelize.TEXT,
      },
      output: {
        type: Sequelize.TEXT,
      },
      sampleInput: {
        type: Sequelize.TEXT,
      },
      sampleOutput: {
        type: Sequelize.TEXT,
      }
      // create_at: {
      //   type: Sequelize.DATE,
      //   allowNull: false,
      // },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('problem'),
};