module.exports = {
  up: (queryInterface, Sequelize) =>
    queryInterface.createTable('problem', {
      prob_no: {
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      user_id: {
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
      time_lim: {
        type: Sequelize.REAL,
      },
      memory_lim: {
        type: Sequelize.SMALLINT,
      },
      create_at: {
        type: Sequelize.DATE,
        allowNull: false,
      },
    }),
  down: (queryInterface, Sequelize) => queryInterface.dropTable('problem'),
};