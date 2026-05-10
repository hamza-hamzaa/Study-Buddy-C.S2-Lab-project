#include "inputvalidation.h"

namespace InputValidation
{
bool isValidName(const QString &name)
{
    return !name.trimmed().isEmpty();
}

bool isValidEmail(const QString &email)
{
    return email.endsWith("@aucegypt.edu");
}

bool isValidId(int id)
{
    return id / 10000 < 90026 && id / 10000 > 90019;
}

bool isValidMajor(const QString &major)
{
    return major != "Major";
}

bool isCourseSelectionWithinLimit(int totalSelected, int maxCourses)
{
    return totalSelected <= maxCourses;
}
}
