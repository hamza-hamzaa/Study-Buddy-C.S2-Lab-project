#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <QString>

namespace InputValidation
{
bool isValidName(const QString &name);
bool isValidEmail(const QString &email);
bool isValidId(int id);
bool isValidMajor(const QString &major);
bool isCourseSelectionWithinLimit(int totalSelected, int maxCourses = 6);
}

#endif // INPUTVALIDATION_H
