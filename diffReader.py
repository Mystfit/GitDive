import subprocess
import pickle
import re

#-----------------------
# Defines
#-----------------------

path = "/Users/mystfit/Sonoromancer"
logCmd = ['git', 'log', '--pretty=format:"GD_commit//%H || GD_commitAuthor//%cn || GD_date//%cd || GD_message//%b"'];
#logCmd = ['git', 'log', '--pretty=oneline'];
diffCmd = ["git", "log", "-p", '--pretty=format:"GD_commit//%H || GD_commitAuthor//%cn || GD_date//%cd || GD_message//%b"']

globalRemoves = 0
globalAdds = 0


#-----------------------
# Classes
#-----------------------

class LogEntry:
	def __init__(self,entry):
		logVars = entry.rstrip('\n').split(" || ");
		
		if(len(logVars) < 2):
			self.hash = ""
			self.author = ""
			self.date = ""
			self.message = ""
		else:
			self.hash = logVars[0].split("//")[1]
			self.author = logVars[1].split("//")[1]
			self.date = logVars[2].split("//")[1]
			self.message = logVars[3].split("//")[1]

class DiffEntry:
	def __init__(self):
		self.fileName = ""
		self.diffType = ""
		self.hunkList = []

class DiffHunk:
	def __init__(self):
		self.startRemoveLines = 0
		self.numRemoveLines= 0
		self.startAddLines = 0
		self.numAddLines= 0
		self.hunkData = []

class CommitEntry:
	def __init__(self, commit, author, date, message):
		self.commit = commit
		self.author = author
		self.date = date
		self.message = message
		self.diffList = []

	# Add a new raw diff to this commit
	def addAndParseDiff(self, diff):
		self.diffList.append(self.parseRawDiff(diff))

	def serializeCommit(self):
		commitText = "***=== Commit Start ===***\n"
		commitText += "== Author: " + commit.author + "\n"
		commitText += "== Date: " + commit.date + "\n"
		commitText += "== Message: " + commit.message + "\n\n"
		commitText += commit.serializeDiffs()
		commitText += "***=== Commit Finish ===***\n\n\n"
		return commitText

	# Convert diffs into a readable string
	def serializeDiffs(self):
		hunkString = ""

		for i in range(len(self.diffList[0])):
			hunkString += "=== Diff Start ===\n"
			diff = self.diffList[0][i]

			for j in range(len(diff.hunkList)):
				hunkString += "--- Hunk Start ---\n"
				for k in range(len(diff.hunkList[j].hunkData)):
					hunkString += diff.hunkList[j].hunkData[k]
				hunkString += "--- Hunk Finish ---\n"
			hunkString += "=== Diff Finish ===\n\n"


		return hunkString + "\n"

	# Convert raw diff lines into diff and hunk objects
	def parseRawDiff(self, diff):
		global globalAdds
		global globalRemoves

		parsedDiff = []
		currentDiff = None
		currentHunk = None

		for i in range(len(diff)):
			currentLine = diff[i];

			#If the line starts with 'diff', then we make a new diff object and save off the current
			if re.match('diff', currentLine):
				# Create new file diff
				currentDiff = DiffEntry()
				parsedDiff.append(currentDiff)
				# fileName = "/" + currentLine.split("diff --git")[1].split(" b/")[0].split(" a/")[1]
				currentDiff.fileName = "Filename"

			#Diff index
			elif(re.match("index ", currentLine)):
				pass

			#Binary file diff information
			elif(re.match("Binary files  ", currentLine)):
				currentDiff.diffType = "binary"

			#File A name
			elif(re.match("--- a/", currentLine)):
				pass

			#File B name
			elif(re.match("\+\+\+ b/", currentLine)):
				pass

			#New hunk section in diff
			elif(re.match("@@ ", currentLine)):
				currentDiff.diffType = "text"
				currentHunk = DiffHunk()
				currentDiff.hunkList.append(currentHunk);

				preDiffLines = currentLine.split(" ")[1].split(",");
				postDiffLines = currentLine.split(" ")[2].split(",");

				currentHunk.startRemoveLines = int(preDiffLines[0][1:])
				currentHunk.startAddLines = int(postDiffLines[0][1:])
				if (len(preDiffLines) > 1): currentHunk.numRemoveLines = int(preDiffLines[1])  
				if (len(postDiffLines) > 1): currentHunk.numAddLines = int(postDiffLines[1])		

			#Currently in a hunk
			else:
				if(currentHunk):
					currentHunk.hunkData.append(currentLine)

					if(currentLine[:1] == "-"):
						globalRemoves += 1
					if(currentLine[:1] == "+"):
						globalAdds += 1
		
		return parsedDiff


def parseDiffLog(diffFile):
	currLn = ""
	commit = None
	commitList = []
	log = None

	diffBlock = []

	for i in range(len(diffFile)):
		currLn = diffFile[i]

		# Check for a new commit log entry 
		if(re.match('GD_commit//', currLn)):

			log = LogEntry(currLn)

			if(commit):
				commit.addAndParseDiff(diffBlock)
				commitList.append(commit)
				diffBlock = []

			#Parse commit information before setting up new commit obj
			commit = CommitEntry(log.commit, log.author, log.date, log.message)

		else:
			diffBlock.append(currLn)

	return commitList



 






#-----------------------
# Program start
#-----------------------

# logStream = subprocess.Popen(logCmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd=path)
# log = logStream.stdout.read().replace('\n\"\n', '\n').split("\n")

parsedLogs = []
commitList = []
diffFile  = open('diffFile.log', 'w')

diffStream = subprocess.Popen(diffCmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd=path)

parsedDiffLog = parseDiffLog(diffStream.stdout.readlines())

for i in range(len(parsedDiffLog)):
	diffFile.write(parsedDiffLog[i].serializeCommit())


# for i in range(len(log)):
# 	truncLog = log[i][1:]
# 	if(truncLog == ""): continue

# 	parsedLogs.append(LogEntry(truncLog))

# 	# Don't do a diff on the first commit, nothing to compare against!
# 	if(i == 0): continue

# 	diffCmd = ["git", "diff", parsedLogs[len(parsedLogs)-2].hash, parsedLogs[len(parsedLogs)-1].hash ]
# 	diffStream = subprocess.Popen(diffCmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd=path)
	
# 	commit = CommitEntry(parsedLogs[i].hash, parsedLogs[i].author, parsedLogs[i].date, parsedLogs[i].message)
# 	commit.addAndParseDiff(diffStream.stdout.readlines())
	

# 	commitList.append(commit)

print str(globalAdds) + " lines added"
print str(globalRemoves) + " lines removed"


# -- Dump parsed diff file to pickled external file for transfer to cinder --
# pickle.dump(commits, diffFile)
