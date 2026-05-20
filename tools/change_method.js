const processString = require('./lib/extendContent.js');
const readFileSync = require('./lib/readFile.js');
const getCommandFromCLI = require('./lib/input.js');
const updateMethodFile = require('./lib/updateMethod.js');


async function askDeepSeek(question, API_KEY) {
  const response = await fetch('https://openrouter.ai/api/v1/chat/completions', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': API_KEY
    },
    body: JSON.stringify({
      model: "deepseek/deepseek-r1-0528",  // Replace with the actual model name
      messages: [
        { role: "user", content: question }
      ],
      max_tokens : 7000,
      temperature: 0.7
    })
  });

  if (!response.ok) {
    console.error("API Error:", await response.text());
    return;
  }

  const data = await response.json();
  // console.log("DeepSeek Answer:\n", data.choices[0].message.content);
  const newMethod = data.choices[0].message.content
  updateMethodFile(newMethod);
}

// Example usage

const API_KEY = getCommandFromCLI("Enter the API_KEY: ")
const input = getCommandFromCLI("Enter the prompt: ");
console.log("Scraping the text..");
const content = readFileSync('./tools/prompt/method.txt');
const extendedContent = processString(content, input);
// console.log(extendedContent);
console.log("Asking Deepseek..");
const BEARER_API_KEY = `Bearer ${API_KEY}`
askDeepSeek(extendedContent, BEARER_API_KEY);

