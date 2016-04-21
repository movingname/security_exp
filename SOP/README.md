

Task 1:

See the corresponding files in this folder.

In the first response from the server, there is an entry in the HTTP header that sets the cookie:

    Set-Cookie: PHPSESSID=hv1fadv6ml8casugb0bkvs9fl6; path=/

Task 2:

When trying to load Google into the iframe, we see that the GET requests succeeded but the browser prevents the loading.

    [09:40:20.316] GET http://www.google.com/ [HTTP/1.1 302 Found 98ms]
    [09:40:20.428] GET https://www.google.com/?gws_rd=ssl [HTTP/1.1 200 OK 446ms]
    [09:40:20.823] Load denied by X-Frame-Options: https://www.google.com/?gws_rd=ssl does not permit cross-origin framing.

Loading the navitation.html in the iframe with port 8080 works. But there are some restrictions for
the parent:
- cannot read the frame's cookie
- cannot access dom properties, such as URL and history. IN the console, type main.history and the result is "Permission
denied".

If I try to load www.psu.edu, then the result is similar to navigation.html with port 8080.

Ok, so by default, a website can load another website inside an iframe. But the browser prevents any interaction. A
website can make a step further to set X-Frame-Options so that the website will not be shown in a cross-site iframe at
all, like what Google does.

Task 3:

SOP also applies to XMLHttpRequest. In this example, cross-origin request will receive an exmpty response.

Q: Web servers now support XMLHttpRequest by default? 

Task 4:

Requests from the following HTML components will be allowed to another hosts. This is to support collaboration between websites without having too much security risk.
- img
- script
- a
- iframe

They all initiate a GET request.

Q: anything else?
