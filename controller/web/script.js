const digits = [
  [
    // 0
    { hour: 6, minute: 15 },
    { hour: 9, minute: 30 },
    { hour: 6, minute: 0 },
    { hour: 0, minute: 30 },
    { hour: 3, minute: 0 },
    { hour: 0, minute: 45 },
  ],
  [
    // 1
    { hour: 7.5, minute: 37.5 },
    { hour: 6, minute: 30 },
    { hour: 7.5, minute: 37.5 },
    { hour: 6, minute: 0 },
    { hour: 7.5, minute: 37.5 },
    { hour: 0, minute: 0 },
  ],
  [
    // 2
    { hour: 3, minute: 15 },
    { hour: 9, minute: 30 },
    { hour: 6, minute: 15 },
    { hour: 0, minute: 45 },
    { hour: 0, minute: 15 },
    { hour: 9, minute: 45 },
  ],
  [
    // 3
    { hour: 3, minute: 15 },
    { hour: 9, minute: 30 },
    { hour: 3, minute: 15 },
    { hour: 9, minute: 0 },
    { hour: 3, minute: 15 },
    { hour: 9, minute: 0 },
  ],
  [
    // 4
    { hour: 6, minute: 30 },
    { hour: 6, minute: 30 },
    { hour: 0, minute: 15 },
    { hour: 6, minute: 0 },
    { hour: 7.5, minute: 37.5 },
    { hour: 0, minute: 0 },
  ],
  [
    // 5
    { hour: 6, minute: 15 },
    { hour: 9, minute: 45 },
    { hour: 0, minute: 15 },
    { hour: 6, minute: 45 },
    { hour: 3, minute: 15 },
    { hour: 0, minute: 45 },
  ],
  [
    // 6
    { hour: 6, minute: 15 },
    { hour: 9, minute: 45 },
    { hour: 6, minute: 0 },
    { hour: 6, minute: 45 },
    { hour: 0, minute: 15 },
    { hour: 0, minute: 45 },
  ],
  [
    // 7
    { hour: 3, minute: 15 },
    { hour: 6, minute: 45 },
    { hour: 7.5, minute: 37.5 },
    { hour: 6, minute: 0 },
    { hour: 7.5, minute: 37.5 },
    { hour: 0, minute: 0 },
  ],
  [
    // 8
    { hour: 6, minute: 15 },
    { hour: 6, minute: 45 },
    { hour: 0, minute: 15 },
    { hour: 0, minute: 45 },
    { hour: 0, minute: 15 },
    { hour: 0, minute: 45 },
  ],
  [
    // 9
    { hour: 6, minute: 15 },
    { hour: 6, minute: 45 },
    { hour: 3, minute: 0 },
    { hour: 6, minute: 0 },
    { hour: 3, minute: 15 },
    { hour: 0, minute: 45 },
  ],
];

const happyDigit = Array(6).fill({ hour: 22.5, minute: 7.5 });
const neutralDigit = Array(6).fill({ hour: 7.5, minute: 7.5 });

function showSpecialState(digit) {
  stopClock();
  for (let x = 0; x < 4; x++) {
    setDigit(x, digit);
  }
  window.setTimeout(() => startClock(), 10000);
}

function hourToDegrees(hour) {
  return hour * (360 / 12) - 90;
}

function minuteToDegrees(minute) {
  return minute * (360 / 60) - 90;
}

function setHands(id, hour, minute) {
  const clock = document.querySelector(`.clock--${id}`);
  clock.style.setProperty(`--small-hand`, `${hourToDegrees(hour) + 360}deg`);
  clock.style.setProperty(
    `--large-hand`,
    `${minuteToDegrees(minute) - 360}deg`
  );
}

function setDigit(id, values) {
  for (let x = 0; x < 6; x++) {
    setHands(id * 6 + x, values[x].hour, values[x].minute);
  }
}

function setTime(time) {
  setDigit(0, digits[time.charAt(0)]);
  setDigit(1, digits[time.charAt(1)]);
  setDigit(2, digits[time.charAt(3)]);
  setDigit(3, digits[time.charAt(4)]);
}

let state;
let interval;

function startClock() {
  state = "----";
  interval = window.setInterval(() => {
    const time = new Date(Date.now() + 10000).toTimeString();
    if (time !== state) {
      setTime(time);
      state = time;
    }
  }, 1000);
}

function stopClock() {
  clearInterval(interval);
}
