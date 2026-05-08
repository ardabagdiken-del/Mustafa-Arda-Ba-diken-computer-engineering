/**
 * Exercise 4: JavaScript & the DOM
 * ==================================
 * Complete each task below. Read the README.md for full instructions.
 * Open the browser console (F12) to debug.
 */

// ============================================================
// TASK 1 — Console Warmup
// ============================================================

// TODO 1a: Select the element with id "main-title" and change its text
const mainTitle = document.getElementById('main-title');
mainTitle.textContent = "DOM Mastery 🚀";

// TODO 1b: Select ALL elements with class "card", log how many there are
const cards = document.querySelectorAll('.card');
console.log(`Total cards found: ${cards.length}`);

// TODO 1c: Select the element with id "target-box" and change its background
const targetBox = document.getElementById('target-box');
targetBox.style.backgroundColor = "#6c5ce7"; // A nice purple
targetBox.style.color = "white";


// ============================================================
// TASK 2 — Click Counter
// ============================================================

const countDisplay = document.querySelector('#count-display');
// TODO: get references to the three buttons
const btnInc = document.querySelector('#btn-increment');
const btnDec = document.querySelector('#btn-decrement');
const btnReset = document.querySelector('#btn-reset');

let count = 0;

// Helper: update the display and apply color classes
function updateCountDisplay() {
  countDisplay.textContent = count;
  
  // Logic for classes
  if (count === 0) {
    countDisplay.classList.add('zero');
    countDisplay.classList.remove('high');
  } else if (count > 5) {
    countDisplay.classList.add('high');
    countDisplay.classList.remove('zero');
  } else {
    countDisplay.classList.remove('zero', 'high');
  }
}

// TODO: Add click event listeners
btnInc.addEventListener('click', () => {
  count++;
  updateCountDisplay();
});

btnDec.addEventListener('click', () => {
  if (count > 0) {
    count--;
    updateCountDisplay();
  }
});

btnReset.addEventListener('click', () => {
  count = 0;
  updateCountDisplay();
});

updateCountDisplay();


// ============================================================
// TASK 3 — Dynamic List Builder
// ============================================================

const listInput = document.querySelector('#list-input');
const dynamicList = document.querySelector('#dynamic-list');
const btnAdd = document.querySelector('#btn-add-item');

btnAdd.addEventListener('click', function() {
  const value = listInput.value.trim();

  // 2. Validation
  if (value === "") {
    listInput.style.border = "2px solid red";
    setTimeout(() => listInput.style.border = "", 500);
    return;
  }

  // 3 & 4. Create and set content
  const li = document.createElement('li');
  li.innerHTML = `${value} <button class="delete-btn">×</button>`;

  // 5. Append
  dynamicList.appendChild(li);

  // 6. Reset
  listInput.value = "";
  listInput.focus();
});

// TODO: Handle delete buttons via Event Delegation
dynamicList.addEventListener('click', function(event) {
  if (event.target.classList.contains('delete-btn')) {
    const itemToRemove = event.target.parentElement;
    itemToRemove.remove();
  }
});


// ============================================================
// TASK 4 — Show / Hide Toggle
// ============================================================

const toggleBtn = document.querySelector('#btn-toggle');
const detailsDiv = document.querySelector('.details');

toggleBtn.addEventListener('click', () => {
  const isHidden = detailsDiv.classList.toggle('hidden');
  toggleBtn.textContent = isHidden ? "Show Details" : "Hide Details";
});


// ============================================================
// TASK 5 — Color Mixer
// ============================================================

const sliderR = document.querySelector('#slider-r');
const sliderG = document.querySelector('#slider-g');
const sliderB = document.querySelector('#slider-b');
const colorPreview = document.querySelector('#color-preview');
const hexDisplay = document.querySelector('#hex-display');

// Reference spans for showing numerical values
const spanR = document.querySelector('#val-r');
const spanG = document.querySelector('#val-g');
const spanB = document.querySelector('#val-b');

function updateColor() {
  const r = parseInt(sliderR.value);
  const g = parseInt(sliderG.value);
  const b = parseInt(sliderB.value);

  // TODO: Update numerical spans
  spanR.textContent = r;
  spanG.textContent = g;
  spanB.textContent = b;

  // TODO: Set background
  const colorString = `rgb(${r}, ${g}, ${b})`;
  colorPreview.style.backgroundColor = colorString;

  // TODO: Update hex display
  const rHex = r.toString(16).padStart(2, '0');
  const gHex = g.toString(16).padStart(2, '0');
  const bHex = b.toString(16).padStart(2, '0');
  hexDisplay.textContent = `#${rHex}${gHex}${bHex}`.toUpperCase();
}

// TODO: Add 'input' event listeners
[sliderR, sliderG, sliderB].forEach(slider => {
  slider.addEventListener('input', updateColor);
});

updateColor(); 
