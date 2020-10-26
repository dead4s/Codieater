module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('history', {
      mark_no: {
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      prob_no: {
        type: Sequelize.INTEGER,
        references: {
              model: 'problem',
              key: 'prob_no',
        },
        allowNull: false,
      },
      user_id: {
        type: Sequelize.INTEGER,
        references: {
          model: 'user',
          key: 'idx',
        }
      },
      code: {
        type: Sequelize.TEXT,
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
      create_at: {
        type: Sequelize.DATE,
        allowNull: false,
      },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('history'),
};