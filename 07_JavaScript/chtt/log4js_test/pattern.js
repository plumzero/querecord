
import log4js from 'log4js';

log4js.configure({
    appenders: {
        everything: {
            type: 'file',
            filename: 'pattern.log',
            layout: {
                type: 'pattern',
                pattern: '%d{hh:mm:ss:SSS} [%p] %f{1}:%l %m'
            }
        }
    },
    categories: {
        default: { appenders: [ 'everything' ], level: 'info', enableCallStack: true }
    }
});
  
const logger = log4js.getLogger('');
logger.info('Test log message');
logger.debug('I will be logged in all-the-logs.log');
logger.trace("Entering cheese testing");
logger.debug("Got cheese.");
logger.info("Cheese is Comté.");
logger.warn("Cheese is quite smelly.");
logger.error("Cheese is too ripe!");
logger.fatal("Cheese was breeding ground for listeria.");
  