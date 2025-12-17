class Button {
	constructor(x, y, tag) {
		this.x = x;
		this.y = y;
    this.width = 450;
    this.height = 150;
    this.tag = tag;
	}

    display() {
        push();
        
        // If mouse is hovering button...
        if(mouseX > this.x && mouseX < this.x + this.width && mouseY > this.y && mouseY < this.y +this.height) {
          //print("Over");
          fill(200, 75);
        }
        else {
          noFill();
        }

        stroke(255);
        rect(this.x, this.y, this.width, this.height, 10);
        pop();

        push();
        fill(255);
        textSize(24);
        if (this.tag == 1) {
            image(rickImg, this.x + 10, this.y + 25, 100, 100);
            text("Never Gonna Give You Up", this.x + 120, this.y + 70);
            textSize(15);
            text("Rick Astley", this.x + 120, this.y + 90);
        }
        else if (this.tag == 2) {
            image(marioImg, this.x + 10, this.y + 25, 100, 100);
            text("Overworld Theme", this.x + 120, this.y + 70);
            textSize(15);
            text("Koji Kondo", this.x + 120, this.y + 90);
        }
        else if (this.tag == 3) {
            image(pirateImg, this.x + 10, this.y + 25, 100, 100);
            text("He's a Pirate", this.x + 120, this.y + 70);
            textSize(15);
            text("Klaus Badelt and Hans Zimmer", this.x + 120, this.y + 90);
        }
        else {
            image(tetrisImg, this.x + 10, this.y + 25, 100, 100)
            text("Korobeiniki", this.x + 120, this.y + 70);
            textSize(15);
            text("Nikolay Nekrasov", this.x + 120, this.y + 90);
        }
        pop();
    }
}

class Particle {
  constructor() {
    this.reset();

    // Initialize colors
    this.col = color(255, 100);
    this.startCol = this.col;
    this.targetCol = this.col;
    this.lerpAmt = 1;
    this.potValue = 1;
  }

  reset() {
    this.x = random(width);
    this.y = height + random(20, 100);
    this.size = random(10, 100);
    this.speed = random(0.5, 2);
    this.xOffset = random(1000);
  }

  setTargetColor(newColor) {
    this.startCol = this.col;
    this.targetCol = color(newColor);
    this.lerpAmt = 0;
  }

  update() {
    if (inData) {
      if (inData < 4 && inData > 0) {
        if (this.potValue != inData) {
          this.potValue = inData;
        }
      }
    }

    

    // Rise
    this.y -= this.speed / this.potValue;
    print(this.potValue);
    // Wobble
    this.x += map(noise(this.xOffset), 0, 1, -1.5, 1.5);
    this.xOffset += 0.01;

    // If offscreen reset
    if (this.y < -this.size) this.reset();

    // Lerp if able
    if (this.lerpAmt < 1) {
      this.lerpAmt += 0.02;

      if (this.startCol && this.targetCol) {
        this.col = lerpColor(this.startCol, this.targetCol, this.lerpAmt);
      }
    }
  }

  display() {
    noStroke();
    fill(this.col);
    ellipse(this.x, this.y, this.size);
  }
}
