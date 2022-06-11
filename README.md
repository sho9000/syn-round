# syn-round
simple application to round/blur the synapse x ui
<br />along with a nice looking theme

---

### how to use it:
Copy *round.exe* and *round_options.json* **into your Synapse launcher folder**.
![](https://cdn.discordapp.com/attachments/876284350499540995/985093409251401758/unknown.png)

<br /> I also recommend dragging my *bin* folder into your Synapse launcher folder to get the custom theme. For the font to work, install Quicksand font I supplied in the repo
<br />

### configuring options (*round_options.json*):
here is an example of what round_options.json will looks like:
```json
{
  "SynX File": "SYNAPSE FILE NAME GOES HERE",
  "Rounding": {
	  "Enabled": true,
	  "Small": false
  },
  "Blur": false
}
```
where it says SYNAPSE FILE NAME GOES HERE
you need to find the synapse exe from ***INSIDE YOUR *bin* FOLDER!***

### NOTE THAT THERE WILL BE 2 SYNAPSE EXE FILES, SIMPLY PICK THE ONE WITH THE LARGEST FILE SIZE, FOR ME IT WAS THE FIRST ONE!
![](https://cdn.discordapp.com/attachments/876284350499540995/985089667185639494/unknown.png)

# RUNNING THE PROGRAM:
once you have followed all the steps and chosen your settings, **just run *round.exe***
**it should automatically start synapse for you**.


# screenshots:
Here I made my background color very transparent to get a more glassy look.
<br />You can edit your background color in theme-wpf.json in your bin folder.
<br />my round_options: *blur: true, rounding: true, small: false*
<br /> Warning: enabling blur will make your window lag bit while dragging. this is due to the windows api having an unoptimized blur method
![](https://cdn.discordapp.com/attachments/876284350499540995/985088957085794344/unknown.png)

Here I have a slightly darker and less transparent background color
<br />my round_options: *blur: true, rounding: true, small: false*
![](https://cdn.discordapp.com/attachments/876284350499540995/985088086725759047/unknown.png)

Here I made the background not transparent, and set small rounding
<br />my round_options: *blur: false, rounding: true, small: true*
![](https://cdn.discordapp.com/attachments/876284350499540995/985089301568180254/unknown.png)
