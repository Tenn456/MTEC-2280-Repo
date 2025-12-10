class Button {
	constructor(x, y, tag) {
		this.x = x;
		this.y = y;
        this.width = 350;
        this.height = 150;
        this.tag = tag;
	}

    display() {
        push();
        
        // If mouse is hovering button...
        if(mouseX > this.x && mouseX < this.x + this.width && mouseY > this.y && mouseY < this.y +this.height) {
            fill(100);
        }
        else {
            fill(255);
        }
        
        rect(this.x, this.y, this.width, this.height);
        pop();

        push();
        fill(0);
        textSize(24);
        if (this.tag == 1) {
            text("Never Gonna Give You Up", 275, 280);
        }
        else if (this.tag == 2) {
            text("Mario Theme", 720, 280);
        }
        else if (this.tag == 3) {
            // Song name and pos here
        }
        else {
            // Song name and pos here
        }
        pop();
    }
}