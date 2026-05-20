const readline = require('readline');

function getCommandFromCLI(question = 'Enter command: ') {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });

  let command;
  
  // Sync wrapper around async readline
  rl.question(question, (answer) => {
    command = answer.trim();
    rl.close();
  });

  // Block until input is received
  require('events').EventEmitter.defaultMaxListeners = 0;
  while (!command) {
    require('deasync').sleep(100);
  }

  return command;
}

module.exports = getCommandFromCLI;