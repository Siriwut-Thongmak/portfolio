'use strict';

const score0EL = document.querySelector('#score--0');
const score1EL = document.getElementById('score--1'); // return obj --> id can have 1 and only place
//const diceEL = document.getElementsByClassName('dice'); //return array --> class can use in multiple place
const current0EL = document.getElementById('current--0');
const current1EL = document.getElementById('current--1');
const player0EL = document.querySelector('.player--0');
const player1EL = document.querySelector('.player--1');
const diceEL = document.querySelector('.dice'); //return obj even if it used in many place, return many (array) --> querySelectorAll
const btnNew = document.querySelector('.btn--new');
const btnRoll = document.querySelector('.btn--roll');
const btnHold = document.querySelector('.btn--hold');
let currScore = 0;
let player = 0;
score1EL.textContent = 0;

//diceEL[0].classList.add('hidden'); //refer to 1st position
diceEL.classList.add('hidden');

btnRoll.addEventListener('click', function () {
  const dice = Math.trunc(Math.random() * 6 + 1);
  diceEL.classList.remove('hidden');
  diceEL.src = `dice-${dice}.png`;
  if (dice !== 1) {
    currScore += dice;
    //current0EL.textContent = currScore;
    document.getElementById('current--' + player).textContent = currScore;
  } else {
    currScore = 0;
    document.getElementById('current--' + player).textContent = currScore;
    player = player === 0 ? 1 : 0;
    player0EL.classList.toggle('player--active');
    player1EL.classList.toggle('player--active');
  }
});
