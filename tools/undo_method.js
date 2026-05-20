const fs = require('fs').promises;
const path = require('path');

async function updateMethodFile() {
  const basePath = path.join(__dirname, '..', 'grammar');
  const methodPath = path.join(basePath, 'oldmethod.txt');
  const oldMethodPath = path.join(basePath, 'method.txt');
  
  try {
    try {
      await fs.access(methodPath);
      
      await fs.rename(methodPath, oldMethodPath);
    } catch (err) {
      if (err.code === 'ENOENT') {
        console.log(methodPath);
        throw new Error('oldmethod.txt does not exist');
      }
      throw err;
    }
    
  } catch (error) {
    console.error('Error:', error.message);
    throw error; // Re-throw to allow caller to handle
  }
}

updateMethodFile();