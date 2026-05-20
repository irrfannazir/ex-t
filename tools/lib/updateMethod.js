const fs = require('fs').promises;
const path = require('path');


async function updateMethodFile(uncleanContent) {

  const basePath = path.join(__dirname, '..', '..', 'grammar');
  const methodPath = path.join(basePath, 'method.txt');
  const oldMethodPath = path.join(basePath, 'oldmethod.txt');
  const content = uncleanContent.replace(/^`+|`+$/g, '').trim();
  try {
    // Check if method.txt exists first
    try {
      await fs.access(methodPath);
      
      // Rename existing file
      await fs.rename(methodPath, oldMethodPath);
      console.log('Renamed method.txt to oldmethod.txt');
    } catch (err) {
      if (err.code === 'ENOENT') {
        console.log(methodPath);
        throw new Error('method.txt does not exist');
      }
      throw err;
    }

    // Create new method.txt with content
    await fs.writeFile(methodPath, content);
    console.log('Created new method.txt with provided content');
    
  } catch (error) {
    console.error('Error:', error.message);
    throw error; // Re-throw to allow caller to handle
  }
}

// Export the function
module.exports = updateMethodFile;