require('dotenv').config();

const { env } = process;

const common = {
  database: env.DATABASE,
  host: env.HOST,
  username: 'postgres',
  password: env.PASSWORD,
  dialect: 'postgres',
  define: {
    timestamps: true,
    underscored: true,
  },
};

const config = {
  development: {
    ...common,
  },
  production: {
    ...common,
    pool: {
      max: 10,
      min: 0,
      acquire: 30000,
      idle: 10000,
    },
  },
};

module.exports = config;
