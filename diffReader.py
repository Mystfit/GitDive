import subprocess
import pickle
import re

#-----------------------
# Defines
#-----------------------

path = "/Users/mystfit/Code/Python/Gitdive_Prototypes"
diffCmd = ["git", "log", "-p", "--reverse", '--pretty=format:"GD_commit|-%H||GD_commitAuthor|-%cn||GD_date|-%cd||GD_message|-%B"']

globalRemoves = 0
globalAdds = 0


#-----------------------
# Classes
#-----------------------

class LogEntry:
	def __init__(self,entry):
		logVars = entry[1:].rstrip('\n').split("||");
		
		if(len(logVars) < 2):
			self.commitHash = ""
			self.author = ""
			self.date = ""
			self.message = ""
		else:
			self.commitHash = logVars[0].split("|-")[1]
			self.author = logVars[1].split("|-")[1]
			self.date = logVars[2].split("|-")[1]
			self.message = logVars[3].split("|-")[1]

class DiffEntry:
	def __init__(self):
		self.fileNameA = ""
		self.fileNameB = ""
		self.diffType = "text"
		self.fileMode = "updated"
		self.hunkList = []

	def getFilename(self):
		if(self.fileNameB != "/dev/null"):
			return self.fileNameB	
		elif(self.fileNameA != "/dev/null"):
			return self.fileNameA
		

class DiffHunk:
	def __init__(self):
		self.startRemoveLines = 0
		self.numRemoveLines= 0
		self.startAddLines = 0
		self.numAddLines= 0
		self.hunkData = []

class CommitEntry:
	def __init__(self, commitHash, author, date, message):
		self.commitHash = commitHash
		self.author = author
		self.date = date
		self.message = message
		self.diffList = []

	# Add a new raw diff to this commit
	def addAndParseDiff(self, diff):
		self.diffList.append(self.parseRawDiff(diff))

	def serializeCommit(self):
		commitText = "/***=== Commit begins\n"
		commitText += "== Commit hash: " + self.commitHash + "\n"
		commitText += "== Author: " + self.author + "\n"
		commitText += "== Date: " + self.date + "\n"
		commitText += "== Message: " + self.message + "\n\n"
		commitText += self.serializeDiffs()
		commitText += "\\***=== Commit ends\n\n\n"
		return commitText

	# Convert diffs into a readable string
	def serializeDiffs(self):
		hunkString = ""

		for i in range(len(self.diffList[0])):
			diff = self.diffList[0][i]
			hunkString += "/=== Diff File: " + diff.getFilename() + "\n"

			for j in range(len(diff.hunkList)):
				hunkString += "/--- Code hunk begins\n"
				for k in range(len(diff.hunkList[j].hunkData)):
					hunkString += diff.hunkList[j].hunkData[k]
				hunkString += "\\--- Code hunk ends\n"
			hunkString += "\\=== Diff Finish\n\n"


		return hunkString + "\n"

	# Convert raw diff lines into diff and hunk objects
	def parseRawDiff(self, diff):
		global globalAdds
		global globalRemoves

		parsedDiff = []
		currentDiff = None
		currentHunk = None
		inDiffHeader = False

		for i in range(len(diff)):
			currentLine = diff[i];

			#If the line starts with 'diff', then we make a new diff object and save off the current
			if re.match('diff', currentLine):

				#Set line context to header so we can expect diff metadata
				inDiffHeader = True

				# Create new file diff
				currentDiff = DiffEntry()
				parsedDiff.append(currentDiff)

			if(inDiffHeader):
				#Diff index
				if(re.match("index ", currentLine)):
					pass

				elif(re.match("new file mode", currentLine)):
					currentDiff.fileMode = "added"

				elif(re.match("deleted file mode", currentLine)):
					currentDiff.fileMode = "deleted"

				#Binary file diff information
				elif(re.match("Binary files", currentLine)):
					currentDiff.diffType = "binary"

				#File A name
				elif(re.match("--- a/", currentLine)):
					currentDiff.fileNameA = currentLine.split("--- a/")[1].rstrip("\n")

				#File B name
				elif(re.match("\+\+\+ b/", currentLine)):
					currentDiff.fileNameB = currentLine.split("+++ b/")[1].rstrip("\n")

			#New hunk section in diff
			if(re.match("@@ ", currentLine)):
				currentHunk = DiffHunk()
				currentDiff.hunkList.append(currentHunk);

				preDiffLines = currentLine.split(" ")[1].split(",");
				postDiffLines = currentLine.split(" ")[2].split(",");

				currentHunk.startRemoveLines = int(preDiffLines[0][1:])
				currentHunk.startAddLines = int(postDiffLines[0][1:])
				if (len(preDiffLines) > 1): currentHunk.numRemoveLines = int(preDiffLines[1])  
				if (len(postDiffLines) > 1): currentHunk.numAddLines = int(postDiffLines[1])	

				inDiffHeader = False	

			#Currently in a hunk
			else:
				if(currentHunk and not inDiffHeader):
					currentHunk.hunkData.append(currentLine)

					if(currentLine[:1] == "-"):
						globalRemoves += 1
					if(currentLine[:1] == "+"):
						globalAdds += 1
		
		return parsedDiff


def parseDiffLog(diffStream):
	currLn = ""
	commit = None
	commitList = []
	log = None

	diffBlock = []

	for line in iter(diffStream.readline, ''):

		print line

		# Check for a new commit log entry 
		if(re.match('"GD_commit', line)):

			log = LogEntry(line)

			if(commit):
				commit.addAndParseDiff(diffBlock)
				commitList.append(commit)
				diffBlock = []

			#Parse commit information before setting up new commit obj
			commit = CommitEntry(log.commitHash, log.author, log.date, log.message)

		else:
			diffBlock.append(line)

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

parsedDiffLog = parseDiffLog(diffStream.stdout)

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
