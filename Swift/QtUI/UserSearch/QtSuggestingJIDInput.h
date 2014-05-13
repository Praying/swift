/*
 * Copyright (c) 2013 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014 Kevin Smith and Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <QLineEdit>
#include <QTreeView>
#include <Swiften/Base/boost_bsignals.h>
#include <Swift/Controllers/Contact.h>

namespace Swift {

class ContactListDelegate;
class SettingsProvider;
class ContactListModel;

class QtSuggestingJIDInput : public QLineEdit {
	Q_OBJECT
	public:
		QtSuggestingJIDInput(QWidget* parent, SettingsProvider* settings);
		virtual ~QtSuggestingJIDInput();

		Contact::ref getContact();

		void setSuggestions(const std::vector<Contact::ref>& suggestions);

		boost::signal<void (const JID&)> onUserSelected;

	signals:
		void editingDone();

	protected:
		virtual void keyPressEvent(QKeyEvent* event);

	private:
		void handleSettingsChanged(const std::string& setting);

	private slots:
		void handleClicked(const QModelIndex& index);
		void handleApplicationFocusChanged(QWidget* old, QWidget* now);

	private:
		void positionPopup();
		void showPopup();
		void hidePopup();

	private:
		SettingsProvider* settings_;
		ContactListModel* contactListModel_;
		QTreeView* treeViewPopup_;
		ContactListDelegate* contactListDelegate_;
		Contact::ref currentContact_;
};

}