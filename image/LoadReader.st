| repository package latestVersion |
repository := MCHttpRepository
				location: 'http://source.squeak.org/VMMaker'
				user: 'squeak'
				password: 'squeak'.
package := 'CogTools-Listener'.
"We need to filter-out branches of unbranched packages."
latestVersion := (repository versionNamesForPackageNamed: package) detect:
					[:versionName| (versionName at: package size + 1) = $-].
[| version |
version := (MCCacheRepository default versionNamed: latestVersion)
		ifNil: [repository versionNamed: latestVersion].
 version load.
 version workingCopy repositoryGroup addRepository: repository]
	on: Warning
	do: [:ex|
		(ex messageText beginsWith: 'This package depends on the following classes') ifFalse:
			[ex pass].
		ex resume].

Smalltalk snapshot: true andQuit: true
