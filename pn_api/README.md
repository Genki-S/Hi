Hi
==

## API Usage

```
http://localhost:3000/api/v1/pn_value/URL_ENCODED_JAPANESE_MESSAGE
```

returns:

```
{
  "message": "JAPANESE_MESSAGE",
  "pn_value": PN_VALUE (-1 <= PN_VALUE <= 1)
}
```

## Development Setup

### Install gems

```
$ bundle install
```

### Build and install MeCab

```
$ cd local_gems/mecab-ruby-0.996
$ ruby extconf.rb
$ make install
```

### DB Setup

1. start postgres daemon
2. create role (user) named sixplus
  ```
  $ psql -d postgres
  postgres=# create role sixplus login createdb;
  postgres=# \q
  ```
3. `rake db:create`
4. `rake db:migrate`

### Populate DB

1. positive-negative dictionary (Japanese words)
  ```
  $ rake seeds:pn_jp_words
  ```

1. guest user with default messages
  ```
  $ rake seeds:user:guest
  ```

Problems? Issues?
-----------

Need help? Ask on Stack Overflow with the tag 'railsapps.'

Your application contains diagnostics in the README file. Please provide a copy of the README file when reporting any issues.

If the application doesn’t work as expected, please [report an issue](https://github.com/RailsApps/rails_apps_composer/issues)
and include the diagnostics.

Ruby on Rails
-------------

This application requires:

- Ruby 2.1.0
- Rails 4.1.4

Learn more about [Installing Rails](http://railsapps.github.io/installing-rails.html).

Getting Started
---------------

Documentation and Support
-------------------------

Issues
-------------

Similar Projects
----------------

Contributing
------------

Credits
-------

License
-------
