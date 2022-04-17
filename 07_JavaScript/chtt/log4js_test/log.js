
import log4js from 'log4js';

log4js.configure({
    appenders: {
        everything: { type: 'file', filename: 'log.log' }
    },
    categories: {
        default: { appenders: [ 'everything' ], level: 'info' }
    }
});

const logger = log4js.getLogger();
logger.debug('I will be logged in all-the-logs.log');
logger.trace("Entering cheese testing");
logger.debug("Got cheese.");
logger.info("Cheese is Comté.");
logger.warn("Cheese is quite smelly.");
logger.error("Cheese is too ripe!");
logger.fatal("Cheese was breeding ground for listeria.");

logger.error(`接口 /forward/alpha/historyprofit 异常`, 123);